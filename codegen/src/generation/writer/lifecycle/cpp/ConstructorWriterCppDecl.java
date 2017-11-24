package generation.writer.lifecycle.cpp;

import generation.writer.EntityWriter;
import model.EntityTypeModel;

public class ConstructorWriterCppDecl extends EntityWriter {

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        return "Class();";
    }


}
