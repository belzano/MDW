package generation.driver.cpp;

import com.google.common.collect.ImmutableSet;
import generation.TargetOutput;
import generation.driver.ContextGenDriver;
import generation.driver.FilesystemHelper;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;
import model.EntityModelContext;
import generation.writer.EntityWriter;
import generation.writer.helper.WriterHelperCpp;

import java.nio.file.Paths;
import java.util.stream.Collectors;

public class ContextGenDriverCppDef implements ContextGenDriver {

    private String _outDir;

    public ContextGenDriverCppDef(String outDir) {
        _outDir = outDir;
    }

    @Override
    public void generate(EntityModelContext context){
        for(EntityTypeModel model: context.getEntityModels()) {
            writeEntityCode(model);
        }
        writeContextCode(context);
    }

    public void writeEntityCode(EntityTypeModel entityModel) {
        StringBuffer sourceBuffer = new StringBuffer();
        buildDefinition(entityModel, sourceBuffer);

        EntityTypeDescriptor desc = entityModel.getDescriptor();
        FilesystemHelper.mkFile(getEntityTypeAbsPath(desc), getEntityTypeFileName(desc), sourceBuffer.toString());
    }

    String getEntityTypeAbsPath(EntityTypeDescriptor desc) {
        return Paths.get(_outDir, getEntityTypeRelPath(desc)).toString();
    }

    String getEntityTypeRelPath(EntityTypeDescriptor desc) {
        return desc.getNamespace().stream().collect(Collectors.joining("/"));
    }

    String getEntityTypeFileName(EntityTypeDescriptor desc) {
        return desc.getClassName() + ".cpp";
    }

    public void writeContextCode(EntityModelContext entityModelContext) {
        StringBuffer headerBuffer = new StringBuffer();
        buildContextFiles(entityModelContext, headerBuffer);

        // TODO dump to FS


    }


    void buildDefinition(EntityTypeModel model, StringBuffer buffer) {
        // My own include
        buffer.append(WriterHelperCpp.getIncludes(ImmutableSet.of(model.getDescriptor())));
        // Impl Includes ?

        // namespace _start

        // contents: Lifecyle
        // contents: Features
        for (EntityWriter writer: model.getWriters(TargetOutput.CPP)) {
            buffer.append(writer.writeEntityContent(model));
        }

        // namespace _end

        // global namespace operators
    }

    void buildContextFiles(EntityModelContext entityModelContext, StringBuffer buffer) {

    }

}
