package generation.writer.helper;

import com.google.common.base.Strings;
import com.google.common.collect.ImmutableList;
import model.EntityTypeDescriptor;

import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class WriterHelperCpp extends WriterHelper {

    public static String getNamespaceStart(List<String> namespaces) {
        StringBuilder res = new StringBuilder();
        for (String namespace : namespaces) {
            res.append("namespace ").append(namespace).append(" {").append(EOL);
        }
        return res.toString();
    }

    public static String getNamespaceEnd(List<String> namespaces) {
        return Strings.repeat("}" + EOL, namespaces.size());
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
        String specific = TypeMappingCpp.INCLUDES_MAP.get(desc);
        if (specific != null) {
            return specific;
        }
        String resourceWithPath = String.join("/",
                ImmutableList.<String>builder()
                        .addAll(desc.getNamespace())
                        .add(desc.getClassName())
                        .build());
        return QUOTE + resourceWithPath + ".hpp" + QUOTE;
    }

}
