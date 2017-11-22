package generation;

import model.EntityModel;
import model.EntityModelContext;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

public class CodeGenDriver {

    private String _outDirectory;

    public CodeGenDriver(String outDirectory) throws Exception {
        _outDirectory = outDirectory;
        Files.createDirectories(Paths.get(new File(_outDirectory).toURI()));
    }

    public void generate(TargetOutput target, EntityModelContext context) {
        CodeGenerator generator = getGenerator(target);

        for (EntityModel model : context.getEntityModels()) {
            generator.writeEntityCode(model);
        }
        generator.writeContextCode(context);
    }

    private CodeGenerator getGenerator(TargetOutput target){
        if (target == TargetOutput.CPP) {
            return new CodeGeneratorCpp(_outDirectory);
        }
        return null;
    }

}
