package generation.writer.members.cpp;


import generation.writer.EntityWriter;
import generation.writer.helper.TypeMappingCpp;
import generation.writer.helper.WriterHelperCpp;
import model.EntityDataField;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

import java.util.Set;

public class MembersWriterCppDecl extends EntityWriter {

    public MembersWriterCppDecl() {
        super(Type.MEMBERS);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuilder buffer = new StringBuilder();

        buffer.append("private:" + WriterHelperCpp.EOL);
        for(EntityDataField field : fields) {
            EntityTypeDescriptor typeDesc = TypeMappingCpp.convertType(field.getDescriptor());

            buffer.append(WriterHelperCpp.TAB);
            buffer.append(TypeMappingCpp.qualifiedTypeOf(typeDesc));
            buffer.append(" ");
            buffer.append(field.getMemberName());
            buffer.append(";" + WriterHelperCpp.EOL);
        }
        return buffer.toString();
    }

}