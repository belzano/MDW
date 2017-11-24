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
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

public class RuntimeCompiler {

    private String _tmpDirectory;

    public RuntimeCompiler(String tmpDirectory) throws Exception {
        _tmpDirectory = tmpDirectory;
        Files.createDirectories(Paths.get(new File(_tmpDirectory).toURI()));
    }

    public void buildDir(String rootDir) throws Exception {

        File handle =  new File(rootDir);
        List<String> filesInDir = recursiveCollectFiles(handle);

        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        DiagnosticCollector diagnostics = getDiagnosticListener();

        StandardJavaFileManager fileManager = compiler.getStandardFileManager(diagnostics,  Locale.ENGLISH, Charset.defaultCharset());
        Iterable<? extends JavaFileObject> compilationUnits = fileManager.getJavaFileObjectsFromStrings(filesInDir);

        Iterable<String> options = Arrays.asList("-d", _tmpDirectory, "-sourcepath", rootDir);

        JavaCompiler.CompilationTask task = compiler.getTask(null, fileManager, diagnostics, options,  null, compilationUnits);
        task.call();

        printDiagnostics(diagnostics);
        fileManager.close();
    }

    private List<String> recursiveCollectFiles(File handle) {
        List<String> result = new ArrayList<>();

        if (handle.isFile()) {
            result.add(handle.getPath());
            return result;
        }

        if (handle.isDirectory()) {
            for (File file: handle.listFiles()) {
                result.addAll(recursiveCollectFiles(file));
            }
            return result;
        }
        return result;
    }

    private void printDiagnostics(DiagnosticCollector diagnostics) {
        List<Diagnostic> diagnosticsList =  diagnostics.getDiagnostics();
        for (Diagnostic diagnostic : diagnosticsList) {
            System.out.println(diagnostic.getCode());
            System.out.println(diagnostic.getKind());
            System.out.println(diagnostic.getPosition());
            System.out.println(diagnostic.getStartPosition());
            System.out.println(diagnostic.getEndPosition());
            System.out.println(diagnostic.getSource());
            System.out.println(diagnostic.getMessage(null));
        }
    }

    DiagnosticCollector getDiagnosticListener() {
        DiagnosticCollector<JavaFileObject> diagnostics = new DiagnosticCollector<>();
        return diagnostics;
    }

}
