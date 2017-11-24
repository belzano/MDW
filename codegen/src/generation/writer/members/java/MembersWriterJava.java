package generation.writer.members.java;


import generation.writer.EntityWriter;
import model.EntityTypeModel;

public class MembersWriterJava extends EntityWriter {

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        return "private String _todo; ";
    }

}