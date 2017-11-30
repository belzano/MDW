package generation.writer.helper;

import com.google.common.collect.ImmutableMap;
import model.EntityTypeDescriptor;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

public class TypeMappingCpp {

    public static String qualifiedTypeOf(EntityTypeDescriptor typeDesc) {
        return WriterHelperCpp.getNamespacePrefix(typeDesc.getNamespace()) + typeDesc.getClassName();
    }

    public static EntityTypeDescriptor convertType(EntityTypeDescriptor desc) {
        EntityTypeDescriptor conv = CONVERSION_MAP.get(desc);
        if (conv != null) {
            return conv;
        }
        return desc;
    }

    static String[] NAMESPACE_NONE = new String[] {};
    static String[] NAMESPACE_STD = new String[] {"std"};

    static Map<EntityTypeDescriptor, EntityTypeDescriptor> CONVERSION_MAP =
            ImmutableMap.<EntityTypeDescriptor, EntityTypeDescriptor>builder()
                    .put(EntityTypeDescriptor.of(int.class),        EntityTypeDescriptor.of(NAMESPACE_NONE, "int"))
                    .put(EntityTypeDescriptor.of(long.class),       EntityTypeDescriptor.of(NAMESPACE_NONE, "long"))
                    .put(EntityTypeDescriptor.of(String.class),     EntityTypeDescriptor.of(NAMESPACE_STD, "string"))
                    .put(EntityTypeDescriptor.of(Map.class),        EntityTypeDescriptor.of(NAMESPACE_STD, "map"))
                    .put(EntityTypeDescriptor.of(List.class),       EntityTypeDescriptor.of(NAMESPACE_STD, "list"))
                    .put(EntityTypeDescriptor.of(Set.class),        EntityTypeDescriptor.of(NAMESPACE_STD, "set"))
                    .put(EntityTypeDescriptor.of(Vector.class),     EntityTypeDescriptor.of(NAMESPACE_STD, "vector"))
                    .build();


    static Map<EntityTypeDescriptor, String> INCLUDES_MAP =
            ImmutableMap.<EntityTypeDescriptor, String>builder()
                    .put(EntityTypeDescriptor.of(int.class),        "<cstdint>")
                    .put(EntityTypeDescriptor.of(long.class),       "<cstdint>")
                    .put(EntityTypeDescriptor.of(String.class),     "<string>")
                    .put(EntityTypeDescriptor.of(Map.class),        "<map>")
                    .put(EntityTypeDescriptor.of(List.class),       "<list>")
                    .put(EntityTypeDescriptor.of(Set.class),        "<set>")
                    .put(EntityTypeDescriptor.of(Vector.class),     "<vector>")
                    .build();


}
