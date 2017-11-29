package generation.writer.accessors.cpp;


import annotation.accessors.Getter;
import annotation.accessors.Setter;
import generation.writer.EntityWriter;
import generation.writer.helper.TypeMappingCpp;
import generation.writer.helper.WriterHelperCpp;
import model.EntityDataField;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

import java.util.Set;

public class AccessorWriterCppDef extends EntityWriter {

    public AccessorWriterCppDef() {
        super(Type.CONTENT_ACCESSORS);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuilder buffer = new StringBuilder();

        EntityTypeDescriptor entityTypeDesc = entityModel.getDescriptor();
        for(EntityDataField field : fields) {

            EntityTypeDescriptor typeDesc = TypeMappingCpp.convertType(field.getDescriptor());

            if (field.hasAnnotation(Getter.class)) {
                buffer.append("const ");
                buffer.append(TypeMappingCpp.qualifiedTypeOf(typeDesc));
                buffer.append("& ");
                buffer.append(WriterHelperCpp.getNamespacePrefix(entityTypeDesc.getNamespace()));
                buffer.append(entityTypeDesc.getClassName());
                buffer.append("::");
                buffer.append(field.getGetterName());
                buffer.append("() const {" + WriterHelperCpp.EOL);
                buffer.append(WriterHelperCpp.TAB + "return ");
                buffer.append(field.getMemberName());
                buffer.append(";" + WriterHelperCpp.EOL + "}" + WriterHelperCpp.EOL + WriterHelperCpp.EOL);
            }

            if (field.hasAnnotation(Setter.class)) {
                buffer.append("void ");
                buffer.append(WriterHelperCpp.getNamespacePrefix(entityTypeDesc.getNamespace()));
                buffer.append(entityTypeDesc.getClassName());
                buffer.append("::");
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