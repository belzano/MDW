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

public class AccessorWriterCppDecl extends EntityWriter {

    public AccessorWriterCppDecl() {
        super(Type.CONTENT_ACCESSORS);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuffer buffer = new StringBuffer();
        buffer.append("public:" + WriterHelperCpp.EOL);

        for(EntityDataField field : fields) {

            EntityTypeDescriptor typeDesc = TypeMappingCpp.convertType(field.getDescriptor());

            if (field.hasAnnotation(Getter.class)) {
                buffer.append(WriterHelperCpp.TAB);
                buffer.append("const ");
                buffer.append(TypeMappingCpp.qualifiedTypeOf(typeDesc));
                buffer.append("& ");
                buffer.append(field.getGetterName());
                buffer.append("() const;" + WriterHelperCpp.EOL);
            }

            if (field.hasAnnotation(Setter.class)) {
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