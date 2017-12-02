package generation.writer.accessors.java;

import annotation.accessors.Getter;
import annotation.accessors.Setter;
import generation.writer.EntityWriter;
import generation.writer.helper.TypeMappingCpp;
import generation.writer.helper.WriterHelper;
import model.EntityDataField;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

import java.util.Set;

public class AccessorWriterJava extends EntityWriter {

    public AccessorWriterJava() {
        super(Type.ACCESSORS);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        Set<EntityDataField> fields = entityModel.getDataFields();
        StringBuilder buffer = new StringBuilder();

        for(EntityDataField field : fields) {

            EntityTypeDescriptor typeDesc = field.getDescriptor();

            if (field.hasAnnotation(Getter.class)) {
                buffer.append(WriterHelper.TAB);
                buffer.append("public ");
                buffer.append(typeDesc.getClassName());
                buffer.append(" ");
                buffer.append(field.getGetterName());
                buffer.append("() {" + WriterHelper.EOL);

                buffer.append(WriterHelper.TAB + WriterHelper.TAB + "return ");
                buffer.append(field.getMemberName());
                buffer.append(";" + WriterHelper.EOL);

                buffer.append(WriterHelper.TAB + "}" + WriterHelper.EOL + WriterHelper.EOL);
            }

            if (field.hasAnnotation(Setter.class)) {
                buffer.append(WriterHelper.TAB);
                buffer.append("public void ");
                buffer.append(field.getSetterName());
                buffer.append("(");
                buffer.append(typeDesc.getClassName());
                buffer.append(" val) {" + WriterHelper.EOL);

                buffer.append(WriterHelper.TAB + WriterHelper.TAB);
                buffer.append(field.getMemberName());
                buffer.append(" = val;" + WriterHelper.EOL);

                buffer.append(WriterHelper.TAB + "}" + WriterHelper.EOL + WriterHelper.EOL);

            }
        }
        return buffer.toString();
    }
}
