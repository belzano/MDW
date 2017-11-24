package generation.driver.java;

import generation.driver.ContextGenDriver;
import model.EntityTypeModel;
import model.EntityModelContext;

public class ContextGenDriverJava implements ContextGenDriver {

    private String _outDir;

    public ContextGenDriverJava(String outDir) {
        _outDir = outDir;
    }

    @Override
    public void generate(EntityModelContext context){
        for(EntityTypeModel model: context.getEntityModels()) {
            writeEntityCode(model);
        }
        writeContextCode(context);
    }

    void writeEntityCode(EntityTypeModel entityModel) {

    }

    void writeContextCode(EntityModelContext entityModelContext) {

    }

}
