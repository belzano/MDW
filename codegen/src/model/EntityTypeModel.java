package model;

import generation.TargetOutput;
import generation.writer.EntityWriter;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class EntityTypeModel {

    private Class<?> _entityClass;
    private Map<TargetOutput, Set<EntityWriter>> _writers = new HashMap<>();
    private Set<EntityTypeDescriptor> _additionalDependencies = new HashSet<>();

    private Set<EntityDataField> _dataFields = new HashSet<>();

    public EntityTypeModel(Class<?> entityClass) {
        _entityClass = entityClass;
    }

    public Class<?> getEntityClass() {
        return _entityClass;
    }

    public EntityTypeDescriptor getDescriptor() {
        return EntityTypeDescriptor.of(_entityClass);
    }

    public EntityTypeDescriptor getParentDescriptor() {
        Class<?> parent = _entityClass.getSuperclass();
        if (parent == null || parent == Object.class)
            return null;
        return EntityTypeDescriptor.of(parent);
    }

    public Set<EntityTypeDescriptor> getDependencies() {
        Set<EntityTypeDescriptor> dependencies = new HashSet<>();

        EntityTypeDescriptor parentDesc = getParentDescriptor();
        if (parentDesc != null) {
            dependencies.add(getParentDescriptor());
        }
        dependencies.addAll(getDataFields().stream().map(entityDataField -> entityDataField.getDescriptor()).collect(Collectors.toSet()));
        dependencies.addAll(_additionalDependencies);

        return dependencies;
    }

    public void addDataField(EntityDataField df) {
        _dataFields.add(df);
    }

    public Set<EntityDataField> getDataFields() {
        return _dataFields;
    }

    public void addAdditionalDependencies(Set<EntityTypeDescriptor> descriptors) {
        _additionalDependencies.addAll(descriptors);
    }

    public void addWriter(TargetOutput target, EntityWriter e) {
        if (_writers.get(target) == null) {
            _writers.put(target, new HashSet<>());
        }
        _writers.get(target).add(e);
    }

    public Set<EntityWriter> getWriters(TargetOutput target) {
        Set<EntityWriter> writers =  _writers.get(target);
        if (writers == null) {
            return new HashSet<>() ;
        }
        return writers;
    }
}
