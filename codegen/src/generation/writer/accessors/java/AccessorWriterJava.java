package generation.writer.accessors.java;

import generation.writer.EntityWriter;
import model.EntityTypeModel;

public class AccessorWriterJava extends EntityWriter {

    public AccessorWriterJava() {
        super(Type.CONTENT_ACCESSORS);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        return "";
    }
}
