package generation.writer.members.java;


import generation.writer.EntityWriter;
import generation.writer.helper.WriterHelper;
import model.EntityDataField;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

import java.util.Set;

public class MembersWriterJava extends EntityWriter {

    public MembersWriterJava() {
        super(Type.MEMBERS);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuilder buffer = new StringBuilder();

        for(EntityDataField field : fields) {
            EntityTypeDescriptor typeDesc = field.getDescriptor();

            buffer.append(WriterHelper.TAB);
            buffer.append("protected ");
            buffer.append(typeDesc.getClassName());
            buffer.append(" ");
            buffer.append(field.getMemberName());
            buffer.append(";" + WriterHelper.EOL);
        }
        return buffer.toString();
    }

}