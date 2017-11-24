package generation.writer.helper;

import com.google.common.collect.ImmutableList;
import com.google.common.collect.ImmutableMap;
import model.EntityTypeDescriptor;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class WriterHelperCpp {

    final public static String QUOTE = "\"";
    final public static String EOL = "\n";
    final public static String TAB = "\t";

    public static String getNamespaceStart(List<String> namespaces) {
        StringBuilder res = new StringBuilder();
        for (String namespace : namespaces) {
            res.append("namespace ").append(namespace).append(" {").append(EOL);
        }
        return res.toString();
    }

    public static String getNamespaceEnd(List<String> namespaces) {
        StringBuilder res = new StringBuilder();
        for (String namespace : namespaces) {
            res.append("}" + EOL);
        }
        return res.toString();
    }

    public static String getNamespacePrefix(List<String> namespaces) {
        StringBuilder res = new StringBuilder();
        for (String namespace : namespaces) {
            res.append(namespace).append("::");
        }
        return res.toString();
    }

    public static String getIncludes(Set<EntityTypeDescriptor> dependencies) {
        Set<String> resources = dependencies.stream()
                .map(entityDescriptor -> WriterHelperCpp.toIncludeResourceFileName(entityDescriptor))
                .collect(Collectors.toSet());

        StringBuilder res = new StringBuilder();
        for (String resource : resources) {
            res.append("#include ").append(resource).append(EOL);
        }
        return res + EOL;
    }

    public static String toIncludeResourceFileName(EntityTypeDescriptor desc) {
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

    static Map<String, String> includeExceptionsMap() {
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
