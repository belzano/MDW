package generation.writer.members.cpp;


import generation.writer.EntityWriter;
import generation.writer.helper.WriterHelperCpp;
import model.EntityDataField;
import model.EntityTypeModel;

import java.util.Set;

public class MembersWriterCppDecl extends EntityWriter {

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuffer buffer = new StringBuffer();
        buffer.append("private:" + WriterHelperCpp.EOL);
        for(EntityDataField field : fields) {
            buffer.append(WriterHelperCpp.TAB);
            buffer.append(WriterHelperCpp.getNamespacePrefix(field.getDescriptor().getNamespace()));
            buffer.append(field.getDescriptor().getClassName());
            buffer.append(" ");
            buffer.append(field.getMemberName());
            buffer.append(";" + WriterHelperCpp.EOL);
        }
        return buffer.toString();
    }

}