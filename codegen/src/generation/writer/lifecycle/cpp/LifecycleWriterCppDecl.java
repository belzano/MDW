package generation.writer.lifecycle.cpp;

import annotation.lifecycle.Constructor;
import annotation.lifecycle.Destructor;
import generation.writer.EntityWriter;
import generation.writer.helper.WriterHelper;
import generation.writer.helper.WriterHelperCpp;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

public class LifecycleWriterCppDecl extends EntityWriter {

    public LifecycleWriterCppDecl() {
        super(Type.LIFECYCLE);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        StringBuilder buffer = new StringBuilder();

        boolean hasContructor = entityModel.hasAnnotation(Constructor.class);
        boolean hasDestructor = entityModel.hasAnnotation(Destructor.class);
        if (hasContructor || hasDestructor) {
            buffer.append("public:");
            buffer.append(WriterHelperCpp.EOL);
        }

        EntityTypeDescriptor typeDesc = entityModel.getDescriptor();

        if (hasContructor) {
            buffer.append(WriterHelper.TAB);
            buffer.append(typeDesc.getClassName());
            buffer.append("::");
            buffer.append(typeDesc.getClassName());
            buffer.append("();" + WriterHelperCpp.EOL);
        }

        if (hasDestructor) {
            buffer.append(WriterHelper.TAB);
            buffer.append("virtual ");
            buffer.append(typeDesc.getClassName());
            buffer.append("::~");
            buffer.append(typeDesc.getClassName());
            buffer.append("();" + WriterHelperCpp.EOL);
        }

        return buffer.toString();
    }

}