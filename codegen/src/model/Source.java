package model;


import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.function.Consumer;

public class Source {

    private Path _sourceFullPath;
    private String _absolutePath;
    private String _relativePath;

    public Path getSourceFullPath() {
        return _sourceFullPath;
    }

    public void setSourceFullPath(Path _sourceFullPath) {
        this._sourceFullPath = _sourceFullPath;
    }

    public String getAbsolutePath() {
        return _absolutePath;
    }

    public void setAbsolutePath(String _absolutePath) {
        this._absolutePath = _absolutePath;
    }

    public String getRelativePath() {
        return _relativePath;
    }

    public void setRelativePath(String _relativePath) {
        this._relativePath = _relativePath;
    }

    public static List<Source> collectSources(String rootDir) throws IOException {
        ArrayList<Source> result = new ArrayList<>();

        Consumer<Path> fileToSourceModel = new Consumer<Path>() {
            @Override
            public void accept(Path path) {
                Source source = new Source();
                result.add(source);
            }
        };

        Files.find(Paths.get(rootDir), Integer.MAX_VALUE, (filePath, fileAttr) -> fileAttr.isRegularFile() && filePath.endsWith(".java"))
             .forEach(fileToSourceModel);
        return result;
    }
}


