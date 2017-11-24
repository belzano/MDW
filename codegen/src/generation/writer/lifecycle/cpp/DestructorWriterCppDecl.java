package generation.writer.lifecycle.cpp;

import generation.writer.EntityWriter;
import model.EntityTypeModel;

public class DestructorWriterCppDecl extends EntityWriter {

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        return "~Class();";
    }

}
