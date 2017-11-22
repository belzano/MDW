package model;

import com.google.common.collect.ImmutableList;

import java.util.List;

public abstract class EntityDescriptor {

    public abstract List<String> getNamespace();

    public abstract String getClassName();

    static EntityDescriptor of(Class<?> clazz) {
        return new EntityDescriptor() {
            @Override
            public List<String> getNamespace() {
                Package pkg = clazz.getPackage();
                if (pkg == null) {
                    return ImmutableList.of();
                }
                String packageName = clazz.getPackage().getName();
                return ImmutableList.copyOf(packageName.split("."));
            }
            @Override
            public String getClassName() {
                return clazz.getSimpleName();
            }
        };
    }

    static EntityDescriptor of(List<String> namespace, String name) {
        return new EntityDescriptor() {
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
