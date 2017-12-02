package generation.driver.java;

import com.google.common.base.Strings;
import com.google.common.collect.ImmutableSet;
import generation.TargetOutput;
import generation.driver.ContextGenDriver;
import generation.driver.FilesystemHelper;
import generation.writer.EntityWriter;
import generation.writer.helper.WriterHelper;
import generation.writer.helper.WriterHelperCpp;
import generation.writer.helper.WriterHelperJava;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;
import model.EntityModelContext;

import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class ContextGenDriverJava extends ContextGenDriver {

    public ContextGenDriverJava(String outDir) {
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
        StringBuffer sourceBuffer = new StringBuffer();
        buildDefinition(entityModel, sourceBuffer);

        EntityTypeDescriptor desc = entityModel.getDescriptor();
        FilesystemHelper.setFile(getEntityTypeAbsPath(desc), getEntityTypeFileName(desc), sourceBuffer.toString());
        return Paths.get(getEntityTypeAbsPath(desc), getEntityTypeFileName(desc)).toString();
    }

    private String getEntityTypeAbsPath(EntityTypeDescriptor desc) {
        return Paths.get(getOutDir(), getEntityTypeRelPath(desc)).toString();
    }

    private String getEntityTypeRelPath(EntityTypeDescriptor desc) {
        return desc.getNamespace().stream().collect(Collectors.joining("/"));
    }

    private String getEntityTypeFileName(EntityTypeDescriptor desc) {
        return desc.getClassName() + ".java";
    }

    void buildDefinition(EntityTypeModel model, StringBuffer buffer) {
        Map<EntityWriter.TypeGroup, Set<EntityWriter>> writers = model.getWritersByTypeGroup(TargetOutput.JAVA);

        for (EntityWriter writer:writers.get(EntityWriter.TypeGroup.HEADER)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // My own package
        String entityPackage = WriterHelperJava.getPackage(model.getDescriptor());
        if (!Strings.isNullOrEmpty(entityPackage)) {
            buffer.append("package ");
            buffer.append(entityPackage);
            buffer.append(";" + WriterHelper.EOL + WriterHelper.EOL);
        }

        // import packages
        buffer.append(WriterHelperJava.getImports(model.getDependencies()));

        // Class starts
        buffer.append(getClassDeclarationStart(model.getDescriptor(), model.getParentDescriptor()));

        // contents: Lifecyle, Features, Inlined Accessors, members
        for (EntityWriter writer: writers.get(EntityWriter.TypeGroup.CONTENT)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // class _end
        buffer.append(getClassDeclarationEnd());

        // global namespace operators
        for (EntityWriter writer:writers.get(EntityWriter.TypeGroup.AFTER)) {
            buffer.append(writer.writeEntityContent(model));
        }
    }

    private String getClassDeclarationStart(EntityTypeDescriptor desc, EntityTypeDescriptor parentDesc) {
        String res = "public class "+ desc.getClassName() + " ";
        if (parentDesc != null){
            res += "extends " + parentDesc.getClassName() + " ";
        }
        res += "{";
        return res + WriterHelperCpp.EOL;
    }

    private String getClassDeclarationEnd() {
        return "}" + WriterHelperCpp.EOL;
    }


    private Set<String> writeContextCode(EntityModelContext entityModelContext) {
        return ImmutableSet.of();
    }



}
