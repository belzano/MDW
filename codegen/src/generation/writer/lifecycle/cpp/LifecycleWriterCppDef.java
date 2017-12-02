package generation.writer.lifecycle.cpp;

import annotation.lifecycle.Constructor;
import annotation.lifecycle.Destructor;
import generation.writer.EntityWriter;
import generation.writer.helper.WriterHelperCpp;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

public class LifecycleWriterCppDef extends EntityWriter {

    public LifecycleWriterCppDef() {
        super(Type.LIFECYCLE);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        StringBuilder buffer = new StringBuilder();

        EntityTypeDescriptor typeDesc = entityModel.getDescriptor();

        if (entityModel.hasAnnotation(Constructor.class)) {
            buffer.append(typeDesc.getClassName());
            buffer.append("::");
            buffer.append(typeDesc.getClassName());
            buffer.append("() {" + WriterHelperCpp.EOL);
            buffer.append(" ");
            buffer.append( WriterHelperCpp.EOL);
            buffer.append("}" + WriterHelperCpp.EOL + WriterHelperCpp.EOL);
        }

        if (entityModel.hasAnnotation(Destructor.class)) {
            buffer.append(typeDesc.getClassName());
            buffer.append("::~");
            buffer.append(typeDesc.getClassName());
            buffer.append("() {" + WriterHelperCpp.EOL);
            buffer.append(" ");
            buffer.append( WriterHelperCpp.EOL);
            buffer.append("}" + WriterHelperCpp.EOL + WriterHelperCpp.EOL);
        }

        return buffer.toString();
    }

}