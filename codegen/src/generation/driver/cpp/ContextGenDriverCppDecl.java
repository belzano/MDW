package generation.driver.cpp;

import com.google.common.collect.ImmutableSet;
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
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.StringJoiner;
import java.util.stream.Collectors;

public class ContextGenDriverCppDecl extends ContextGenDriver {

    public ContextGenDriverCppDecl(String outDir) {
        super(outDir);
    }

    @Override
    public Set<String> generate(EntityModelContext context){
        Set<String> files = new HashSet<>();
        for(EntityTypeModel model: context.getEntityModels()) {
            files.add(writeEntityCode(model));
        }
        files.addAll(writeContextCode(context));
        return files;
    }

    private String writeEntityCode(EntityTypeModel entityModel) {
        StringBuffer headerBuffer = new StringBuffer();
        buildDeclaration(entityModel, headerBuffer);

        EntityTypeDescriptor desc = entityModel.getDescriptor();
        FilesystemHelper.setFile(getEntityTypeAbsPath(desc), getEntityTypeFileName(desc),headerBuffer.toString());
        return Paths.get(getEntityTypeAbsPath(desc), getEntityTypeFileName(desc)).toString();
    }

    private String getEntityTypeAbsPath(EntityTypeDescriptor desc) {
        return Paths.get(getOutDir(), getEntityTypeRelPath(desc)).toString();
    }

    private String getEntityTypeRelPath(EntityTypeDescriptor desc) {
        return desc.getNamespace().stream().collect(Collectors.joining("/"));
    }

    private String getEntityTypeFileName(EntityTypeDescriptor desc) {
        return desc.getClassName() + ".hpp";
    }

    private Set<String> writeContextCode(EntityModelContext entityModelContext) {
        StringBuffer headerBuffer = new StringBuffer();
        buildContextFiles(entityModelContext, headerBuffer);

        // TODO FS dump

        return ImmutableSet.<String>of();
    }

    private void buildDeclaration(EntityTypeModel model, StringBuffer buffer) {
        Map<EntityWriter.TypeGroup, Set<EntityWriter>> writers = model.getWritersByTypeGroup(TargetOutput.HPP);

        for (EntityWriter writer: writers.get(EntityWriter.TypeGroup.HEADER)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // Pragma
        buffer.append("#pragma once" + WriterHelperCpp.EOL);

        // Includes
        buffer.append(WriterHelperCpp.getIncludes(model.getDependencies()));

        // namespace _start
        buffer.append(WriterHelperCpp.getNamespaceStart(model.getDescriptor().getNamespace()));

        // Class starts
        buffer.append(getClassDeclarationStart(model.getDescriptor(), model.getParentDescriptor()));

        // contents: Lifecyle, Features, Inlined Accessors, members
        for (EntityWriter writer: writers.get(EntityWriter.TypeGroup.CONTENT)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // class _end
        buffer.append(getClassDeclarationEnd());

        // namespace _end
        buffer.append(WriterHelperCpp.getNamespaceEnd(model.getDescriptor().getNamespace()));

        // global namespace operators
        for (EntityWriter writer: writers.get(EntityWriter.TypeGroup.AFTER)) {
            buffer.append(writer.writeEntityContent(model));
        }
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


    private void buildContextFiles(EntityModelContext entityModelContext, StringBuffer buffer) {

    }


}
