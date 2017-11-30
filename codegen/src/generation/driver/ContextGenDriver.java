package generation.driver;

import model.EntityModelContext;

import java.io.File;
import java.util.Set;

public abstract class ContextGenDriver {

    private String _outDir;

    protected ContextGenDriver(String outDirectory){
        _outDir = outDirectory;
        FilesystemHelper.mkdir(new File(_outDir));
    }

    public String getOutDir() {
        return _outDir;
    }

    public abstract Set<String> generate(EntityModelContext entityModelContext);



}
