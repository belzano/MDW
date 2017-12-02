package generation.driver.cpp;

import com.google.common.collect.ImmutableList;
import com.google.common.collect.ImmutableSet;
import generation.TargetOutput;
import generation.driver.ContextGenDriver;
import generation.driver.FilesystemHelper;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;
import model.EntityModelContext;
import generation.writer.EntityWriter;
import generation.writer.helper.WriterHelperCpp;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class ContextGenDriverCppDef extends ContextGenDriver {

    public ContextGenDriverCppDef(String outDir) {
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

    public String writeEntityCode(EntityTypeModel entityModel) {
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
        return desc.getClassName() + ".cpp";
    }

    private Set<String> writeContextCode(EntityModelContext entityModelContext) {
        StringBuffer headerBuffer = new StringBuffer();
        buildContextFiles(entityModelContext, headerBuffer);

        // TODO dump to FS

        return ImmutableSet.<String>of();
    }


    void buildDefinition(EntityTypeModel model, StringBuffer buffer) {
        Map<EntityWriter.TypeGroup, Set<EntityWriter>> writers = model.getWritersByTypeGroup(TargetOutput.CPP);

        for (EntityWriter writer:writers.get(EntityWriter.TypeGroup.HEADER)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // My own include
        buffer.append(WriterHelperCpp.getIncludes(ImmutableSet.of(model.getDescriptor())));
        // Impl Includes ?
        // TODO

        // namespace _start

        // contents: Lifecyle, accessors, features
        for (EntityWriter writer:writers.get(EntityWriter.TypeGroup.CONTENT)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // namespace _end

        // global namespace operators
        for (EntityWriter writer:writers.get(EntityWriter.TypeGroup.AFTER)) {
            buffer.append(writer.writeEntityContent(model));
        }
    }

    void buildContextFiles(EntityModelContext entityModelContext, StringBuffer buffer) {

    }

}
