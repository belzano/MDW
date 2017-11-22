package model;

import annotation.EntityModelWriter;

import java.lang.reflect.Field;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

public class EntityModel {

    private Class<?> _entityClass;
    private Set<EntityModelWriter> _writers = new HashSet<>();
    private Set<EntityDescriptor> _additionalDependencies = new HashSet<>();

    public EntityModel(Class<?> entityClass) {
        _entityClass = entityClass;
    }

    public Class<?> getEntityClass() {
        return _entityClass;
    }

    public EntityDescriptor getDescriptor() {
        return EntityDescriptor.of(_entityClass);
    }

    public EntityDescriptor getParentDescriptor() {
        Class<?> parent = _entityClass.getSuperclass();
        if (parent == null || parent == Object.class)
            return null;
        return EntityDescriptor.of(parent);
    }

    public Set<EntityDescriptor> getDependencies() {
        Set<EntityDescriptor> dependencies = new HashSet<>();

        EntityDescriptor parentDesc = getParentDescriptor();
        if (parentDesc != null) {
            dependencies.add(getParentDescriptor());
        }
        dependencies.addAll(getDataFields().stream().map(entityDataField -> entityDataField.getDescriptor()).collect(Collectors.toSet()));
        dependencies.addAll(_additionalDependencies);

        return dependencies;
    }

    public Set<EntityDataField> getDataFields() {
        Set<EntityDataField> dataFields = new HashSet<>();
        for (Field field: _entityClass.getDeclaredFields()) {
            if (field.getDeclaringClass() != _entityClass) {
                continue;
            }
            dataFields.add(new EntityDataField(EntityDescriptor.of(field.getType()),
                           field.getName()));
        }
        return dataFields;
    }

    public void addAdditionalDependencies(Set<EntityDescriptor> descriptors) {
        _additionalDependencies.addAll(descriptors);
    }

    public void addWriter(EntityModelWriter e) {
        _writers.add(e);
    }

    public Set<EntityModelWriter> getWriters() {
        return _writers;
    }
}
