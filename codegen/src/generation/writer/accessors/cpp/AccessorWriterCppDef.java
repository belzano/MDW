package generation.writer.accessors.cpp;


import generation.writer.accessors.AccessorWriterHelper;
import generation.writer.helper.TypeMappingCpp;
import generation.writer.helper.WriterHelperCpp;
import model.EntityDataField;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;
import generation.writer.EntityWriter;

import java.util.Set;

public class AccessorWriterCppDef extends EntityWriter {

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuilder buffer = new StringBuilder();

        for(EntityDataField field : fields) {

            EntityTypeDescriptor typeDesc = TypeMappingCpp.convertType(field.getDescriptor());

            if (AccessorWriterHelper.hasAnnotationGetter(field)) {
                buffer.append("const ");
                buffer.append(TypeMappingCpp.qualifiedTypeOf(typeDesc));
                buffer.append("& ");
                buffer.append(field.getGetterName());
                buffer.append("() const {" + WriterHelperCpp.EOL);
                buffer.append(WriterHelperCpp.TAB + "return ");
                buffer.append(field.getMemberName());
                buffer.append(";" + WriterHelperCpp.EOL + "}" + WriterHelperCpp.EOL + WriterHelperCpp.EOL);
            }

            if (AccessorWriterHelper.hasAnnotationSetter(field)) {
                buffer.append("void ");
                buffer.append(WriterHelperCpp.getNamespacePrefix(entityModel.getDescriptor().getNamespace()));
                buffer.append(field.getSetterName());
                buffer.append("(const ");
                buffer.append(TypeMappingCpp.qualifiedTypeOf(typeDesc));
                buffer.append("& val) {" + WriterHelperCpp.EOL);
                buffer.append(WriterHelperCpp.TAB);
                buffer.append(field.getMemberName());
                buffer.append(" = val;" + WriterHelperCpp.EOL);
                buffer.append("}" + WriterHelperCpp.EOL + WriterHelperCpp.EOL);
            }
        }

        return buffer.toString();
    }

}