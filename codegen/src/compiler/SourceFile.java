package compiler;


import com.google.common.base.Strings;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.nio.file.Path;
import java.util.stream.Collectors;

public class SourceFile {
    private String _filename;
    private Path _relativePath;
    private FileInputStream _handle;

    public SourceFile(String filename,
                      Path relativePath,
                      FileInputStream handle) {
        _filename = filename;
        _relativePath = relativePath;
        _handle = handle;
    }

    public String getClassName() {
        String className = _filename.replaceAll(".java", "");
        String packageName = _relativePath.toString().replaceAll("/", ".");
        if (packageName.startsWith("/")) {
            packageName = packageName.substring(1, packageName.length()-1);
        }
        if (Strings.isNullOrEmpty(packageName)) {
            return className;
        }
        return packageName + "." + className;
    }

    public Path getRelativePath() {
        return _relativePath;
    }

    public String getFilename() {
        return _filename;
    }

    public String readCode() throws FileNotFoundException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(_handle));
        return reader.lines().collect(Collectors.joining());
    }
}