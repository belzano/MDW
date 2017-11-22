package generation;

import annotation.EntityModelWriter;
import com.google.common.collect.ImmutableList;
import com.google.common.collect.ImmutableMap;
import model.EntityDescriptor;
import model.EntityModel;
import model.EntityModelContext;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class CodeGeneratorCpp implements CodeGenerator {

    private String _outDir;

    public CodeGeneratorCpp(String outDir) {
        _outDir = outDir;
    }

    @Override
    public void writeEntityCode(EntityModel entityModel) {
        // Source
        StringBuffer sourceBuffer = new StringBuffer();
        buildDefinition(entityModel, sourceBuffer);

        // Header
        StringBuffer headerBuffer = new StringBuffer();
        buildDeclaration(entityModel, headerBuffer);

        System.out.println("Generated definition: \n" + sourceBuffer.toString());
        System.out.println("Generated declaration: \n" + headerBuffer.toString());

        // TODO dump to FS
    }

    @Override
    public void writeContextCode(EntityModelContext entityModelContext) {
        StringBuffer headerBuffer = new StringBuffer();
        buildContextFiles(entityModelContext, headerBuffer);
    }

    void buildDeclaration(EntityModel model, StringBuffer buffer) {
        // Pragma
        buffer.append("#pragma once" + EOL);

        // Includes
        buffer.append(getIncludes(model.getDependencies()));

        // namespace _start
        buffer.append(getNamespaceStart(model.getDescriptor().getNamespace()));
        // Class starts
        buffer.append(getClassDeclarationStart(model.getDescriptor(), model.getParentDescriptor()));

        // contents: Lifecyle
        // contents: Features
        // contents: Inlined Accessors
        // contents: members
        for (EntityModelWriter writer: model.getWriters()) {
            buffer.append(writer.writeEntityContentDeclaration(model));
        }

        // class _end
        buffer.append(getClassDeclarationEnd());
        // namespace _end
        buffer.append(getNamespaceEnd(model.getDescriptor().getNamespace()));

        // global namespace operators
    }

    private String getIncludes(Set<EntityDescriptor> dependencies) {
        Set<String> resources = dependencies.stream()
                .map(entityDescriptor -> toIncludeResourceFileName(entityDescriptor))
                .collect(Collectors.toSet());

        StringBuilder res = new StringBuilder();
        for (String resource : resources) {
            res.append("#include ").append(resource).append(EOL);
        }
        return res + EOL;
    }

    private String getClassDeclarationStart(EntityDescriptor desc, EntityDescriptor parentDesc) {
        String res = "class "+ desc.getClassName() + " ";
        if (parentDesc != null){
            res += ": public " + parentDesc.getClassName() + " ";
        }
        res += "{";
        return res + EOL;
    }

    private String getClassDeclarationEnd() {
        return "};" + EOL;
    }

    private String getNamespaceStart(List<String> namespaces) {
        StringBuilder res = new StringBuilder();
        for (String namespace : namespaces) {
            res.append("namespace ").append(namespace).append(" {").append(EOL);
        }
        return res.toString();
    }

    private String getNamespaceEnd(List<String> namespaces) {
        StringBuilder res = new StringBuilder();
        for (String namespace : namespaces) {
            res.append("}" + EOL);
        }
        return res.toString();
    }

    void buildDefinition(EntityModel model, StringBuffer buffer) {
        // Includes

        // namespace _start

        // contents: Lifecyle
        // contents: Features
        for (EntityModelWriter writer: model.getWriters()) {
            buffer.append(writer.writeEntityContentDefinition(model));
        }

        // namespace _end

        // global namespace operators
    }

    void buildContextFiles(EntityModelContext entityModelContext, StringBuffer buffer) {

    }

    private String toIncludeResourceFileName(EntityDescriptor desc) {
        String descName = desc.getClassName();
        String exception = includeExceptionsMap().get(descName);
        if (exception!= null) {
            return exception;
        }
        String resourceWithPath = String.join("/",
                ImmutableList.<String>builder()
                        .addAll(desc.getNamespace())
                        .add(desc.getClassName())
                        .build());
        return QUOTE + resourceWithPath + ".hpp" + QUOTE;
    }

    private Map<String, String> includeExceptionsMap() {
        return ImmutableMap.<String, String>builder()
                .put("String", "<string>")
                .put("int", "<cstdint>")
                .put("long", "<cstdint>")
                .put("Map", "<map>")
                .put("List", "<list>")
                .put("Set", "<set>")
                .put("Array", "<vector>")
                .build();
    }
}
