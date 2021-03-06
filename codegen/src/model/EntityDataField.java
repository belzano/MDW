package model;

import com.google.common.collect.ComparisonChain;

import java.lang.annotation.Annotation;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

public class EntityDataField implements Comparable<EntityDataField> {

   private EntityTypeDescriptor _fieldType;
   private String _fieldName;

   public Set<Class<? extends Annotation>> _annotations = new HashSet<>();

   public EntityDataField(EntityTypeDescriptor fieldType, String fieldName) {
      _fieldType = fieldType;
      _fieldName = fieldName;
   }

    public Set<Class<? extends Annotation>> getAnnotations() {
        return _annotations;
    }

    public void addAnnotation(Class<? extends Annotation> a) {
        _annotations.add(a);
    }

    public void addAnnotations(Collection<Class<? extends Annotation>> a) {
        _annotations.addAll(a);
    }

    public boolean hasAnnotation(Class<? extends Annotation> clazz) {
        return _annotations.contains(clazz);
    }

    public EntityTypeDescriptor getDescriptor() {
        return _fieldType;
    }

    public String getName() {
        return _fieldName;
    }

    public String getNameCamelCase() {
        return _fieldName.substring(0,1).toUpperCase() +  _fieldName.substring(1, _fieldName.length());
    }

    public String getMemberName() {
        return "_" + _fieldName;
    }

    public String getGetterName() {
        return "get" + getNameCamelCase();
    }

    public String getSetterName() {
        return "set" + getNameCamelCase();
    }

    @Override
    public int compareTo(EntityDataField entityDataField) {
        return ComparisonChain.start()
                .compare(getDescriptor(), entityDataField.getDescriptor())
                .compare(getName(), entityDataField.getName())
                .result();
    }
}
