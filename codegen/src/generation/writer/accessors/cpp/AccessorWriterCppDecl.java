package generation.writer.accessors.cpp;


import generation.writer.EntityWriter;
import generation.writer.accessors.AccessorWriterHelper;
import generation.writer.helper.TypeMappingCpp;
import generation.writer.helper.WriterHelperCpp;
import model.EntityDataField;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

import java.util.Set;

public class AccessorWriterCppDecl extends EntityWriter {

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuffer buffer = new StringBuffer();
        buffer.append("public:" + WriterHelperCpp.EOL);

        for(EntityDataField field : fields) {

            EntityTypeDescriptor typeDesc = TypeMappingCpp.convertType(field.getDescriptor());

            if (AccessorWriterHelper.hasAnnotationGetter(field)) {
                buffer.append(WriterHelperCpp.TAB);
                buffer.append("const ");
                buffer.append(TypeMappingCpp.qualifiedTypeOf(typeDesc));
                buffer.append("& ");
                buffer.append(field.getGetterName());
                buffer.append("() const;" + WriterHelperCpp.EOL);
            }

            if (AccessorWriterHelper.hasAnnotationSetter(field)) {
                buffer.append(WriterHelperCpp.TAB);
                buffer.append("void ");
                buffer.append(field.getSetterName());
                buffer.append("(const ");
                buffer.append(TypeMappingCpp.qualifiedTypeOf(typeDesc));
                buffer.append("& );" + WriterHelperCpp.EOL);
            }
        }
        return buffer.toString();
    }

}