package generation.driver.cpp;

import generation.TargetOutput;
import generation.driver.ContextGenDriver;
import generation.writer.helper.WriterHelperCpp;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;
import model.EntityModelContext;
import generation.writer.EntityWriter;

public class ContextGenDriverCppDecl implements ContextGenDriver {

    private String _outDir;

    public ContextGenDriverCppDecl(String outDir) {
        _outDir = outDir;
    }

    @Override
    public void generate(EntityModelContext context){
        for(EntityTypeModel model: context.getEntityModels()) {
            writeEntityCode(model);
        }
        writeContextCode(context);
    }

    void writeEntityCode(EntityTypeModel entityModel) {
        // Header
        StringBuffer headerBuffer = new StringBuffer();
        buildDeclaration(entityModel, headerBuffer);

        System.out.println("Generated declaration: \n" + headerBuffer.toString());

        // TODO dump to FS
    }

    void writeContextCode(EntityModelContext entityModelContext) {
        StringBuffer headerBuffer = new StringBuffer();
        buildContextFiles(entityModelContext, headerBuffer);
    }

    private void buildDeclaration(EntityTypeModel model, StringBuffer buffer) {
        // Pragma
        buffer.append("#pragma once" + WriterHelperCpp.EOL);
        // Includes
        buffer.append(WriterHelperCpp.getIncludes(model.getDependencies()));

        // namespace _start
        buffer.append(WriterHelperCpp.getNamespaceStart(model.getDescriptor().getNamespace()));

        // Class starts
        buffer.append(getClassDeclarationStart(model.getDescriptor(), model.getParentDescriptor()));

        // contents: Lifecyle, Features, Inlined Accessors, members
        for (EntityWriter writer: model.getWriters(TargetOutput.HPP)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // class _end
        buffer.append(getClassDeclarationEnd());

        // namespace _end
        buffer.append(WriterHelperCpp.getNamespaceEnd(model.getDescriptor().getNamespace()));

        // global namespace operators
    }


    private String getClassDeclarationStart(EntityTypeDescriptor desc, EntityTypeDescriptor parentDesc) {
        String res = "class "+ desc.getClassName() + " ";
        if (parentDesc != null){
            res += ": public " + parentDesc.getClassName() + " ";
        }
        res += "{";
        return res + WriterHelperCpp.EOL;
    }

    private String getClassDeclarationEnd() {
        return "};" + WriterHelperCpp.EOL;
    }


    void buildContextFiles(EntityModelContext entityModelContext, StringBuffer buffer) {

    }


}
