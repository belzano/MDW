package generation.writer.helper;

import com.google.common.collect.ImmutableList;
import model.EntityTypeDescriptor;

import java.util.Set;
import java.util.stream.Collectors;

public class WriterHelperJava extends WriterHelper {

    public static String getPackage(EntityTypeDescriptor desc) {
        return String.join(".", desc.getNamespace());
    }

    public static String getImports(Set<EntityTypeDescriptor> dependencies) {
        Set<String> resources = dependencies.stream()
                .map(entityDescriptor -> WriterHelperJava.toQualifiedClassName(entityDescriptor))
                .sorted()
                .collect(Collectors.toSet());

        StringBuilder res = new StringBuilder();
        for (String resource : resources) {
            res.append("import ").append(resource).append(";" + EOL);
        }
        return res + EOL;
    }

    public static String toQualifiedClassName(EntityTypeDescriptor desc) {
        return String.join(".",
                ImmutableList.<String>builder()
                        .addAll(desc.getNamespace())
                        .add(desc.getClassName())
                        .build());
    }

}
