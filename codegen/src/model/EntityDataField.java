package model;

import java.lang.annotation.Annotation;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

public class EntityDataField {

   private EntityTypeDescriptor _fieldType;
   private String _fieldName;

   public Set<Annotation> _annotations = new HashSet<>();

   public EntityDataField(EntityTypeDescriptor fieldType, String fieldName) {
      _fieldType = fieldType;
      _fieldName = fieldName;
   }

    public Set<Annotation> getAnnotations() {
        return _annotations;
    }

    public void addAnnotation(Annotation a) {
        _annotations.add(a);
    }

    public void addAnnotations(Collection<Annotation> a) {
        _annotations.addAll(a);
    }

    public boolean hasAnnotation(Class<? extends Annotation> clazz) {
        return getAnnotation(clazz) != null;
    }

    public Annotation getAnnotation(Class<? extends Annotation> clazz) {
        for (Annotation an : _annotations) {
            if (an.getClass() == clazz)
                return an;
        }
        return null;
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


}
