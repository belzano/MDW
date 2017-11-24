package generation.writer.lifecycle.cpp;

import model.EntityTypeModel;
import generation.writer.EntityWriter;

public class DestructorWriterCppDef extends EntityWriter {

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        return "Class::~Class() { }";
    }
}
