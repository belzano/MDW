package generation.driver.cpp;

import generation.TargetOutput;
import generation.driver.ContextGenDriver;
import generation.driver.FilesystemHelper;
import generation.writer.helper.WriterHelperCpp;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;
import model.EntityModelContext;
import generation.writer.EntityWriter;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.FileAttribute;
import java.util.StringJoiner;
import java.util.stream.Collectors;

public class ContextGenDriverCppDecl implements ContextGenDriver {

    private String _outDir;

    public ContextGenDriverCppDecl(String outDir) {
        _outDir = outDir;
        FilesystemHelper.mkdir(new File(_outDir));
    }

    @Override
    public void generate(EntityModelContext context){
        for(EntityTypeModel model: context.getEntityModels()) {
            writeEntityCode(model);
        }
        writeContextCode(context);
    }

    void writeEntityCode(EntityTypeModel entityModel) {
        StringBuffer headerBuffer = new StringBuffer();
        buildDeclaration(entityModel, headerBuffer);

        EntityTypeDescriptor desc = entityModel.getDescriptor();
        FilesystemHelper.mkFile(getEntityTypeAbsPath(desc), getEntityTypeFileName(desc),headerBuffer.toString());
    }

    String getEntityTypeAbsPath(EntityTypeDescriptor desc) {
        return Paths.get(_outDir, getEntityTypeRelPath(desc)).toString();
    }

    String getEntityTypeRelPath(EntityTypeDescriptor desc) {
        return desc.getNamespace().stream().collect(Collectors.joining("/"));
    }

    String getEntityTypeFileName(EntityTypeDescriptor desc) {
        return desc.getClassName() + ".hpp";
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
