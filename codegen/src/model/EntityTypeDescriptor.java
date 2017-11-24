package model;

import com.google.common.collect.ImmutableList;

import java.util.List;

public abstract class EntityTypeDescriptor {

    public abstract List<String> getNamespace();

    public abstract String getClassName();

    public static EntityTypeDescriptor of(Class<?> clazz) {
        return new EntityTypeDescriptor() {
            @Override
            public List<String> getNamespace() {
                Package pkg = clazz.getPackage();
                if (pkg == null) {
                    return ImmutableList.of();
                }
                String packageName = clazz.getPackage().getName();

                return ImmutableList.copyOf(packageName.split("\\."));
            }
            @Override
            public String getClassName() {
                return clazz.getSimpleName();
            }
        };
    }

    public static EntityTypeDescriptor of(List<String> namespace, String name) {
        return new EntityTypeDescriptor() {
            @Override
            public List<String> getNamespace() {
                return namespace;
            }
            @Override
            public String getClassName() {
                return name;
            }
        };
    }

}
