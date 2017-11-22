package compiler;

import com.google.common.collect.ImmutableList;
import com.google.common.collect.ImmutableSet;

import javax.tools.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URI;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class RuntimeCompiler {

    private String _tmpDirectory;

    public RuntimeCompiler(String tmpDirectory) throws Exception {
        _tmpDirectory = tmpDirectory;
        Files.createDirectories(Paths.get(new File(_tmpDirectory).toURI()));
    }

    public void buildDir(String rootDir) throws Exception {
        File handle =  new File(rootDir);
        if (! handle.isDirectory()) {
            return;
        }

        for (File file: handle.listFiles()){
            buildRecursive(Paths.get(""), file);
        }
    }

    private void buildRecursive(Path relPath, File handle) throws Exception {
        if (handle.isFile()) {
            buildSourceFile(new SourceFile(handle.getName(), relPath, new FileInputStream(handle.getPath())));
            return;
        }

        if (handle.isDirectory()) {
            Path subPath = Paths.get(relPath.toString(),  handle.getName());
            for (File file: handle.listFiles()) {
                buildRecursive(subPath, file);
            }
            return;
        }

        System.err.println("Skipping file " + handle.getPath());
    }

    private void buildSourceFile(SourceFile source) throws Exception {

        Path sourcePath = Paths.get(_tmpDirectory, source.getRelativePath().toString(), source.getFilename());
        Files.createDirectories(sourcePath.getParent());

        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        SimpleJavaFileObject jfo = new SimpleJavaFileObject(URI.create(""), JavaFileObject.Kind.SOURCE) {
           @Override
            public CharSequence getCharContent(boolean var1) throws IOException {
               return source.readCode();
            }
        };
        Iterable<? extends JavaFileObject> fileObjects = ImmutableList.of(jfo).asList();

        StandardJavaFileManager mgr = compiler.getStandardFileManager(null, null, null);
        mgr.setLocation(StandardLocation.CLASS_OUTPUT, ImmutableSet.of(Paths.get(_tmpDirectory).toFile()).asList());

        JavaCompiler.CompilationTask task = compiler.getTask(null, mgr, null, null, null, fileObjects);
        task.call();

        URL classUrl = new File(_tmpDirectory).toURI().toURL();
        URLClassLoader classLoader = URLClassLoader.newInstance(new URL[]{classUrl});
        String className = source.getClassName();
        Class<?> clazz = Class.forName(className, true, classLoader);
        System.out.println("Built " + clazz);
    }

}
