package model;

public class EntityDataField {

   private EntityDescriptor _fieldType;
    private String _fieldName;

   public EntityDataField(EntityDescriptor fieldType, String fieldName) {
      _fieldType = fieldType;
      _fieldName = fieldName;
   }

    public EntityDescriptor getDescriptor() {
        return _fieldType;
    }

    public String getName() {
        return _fieldName;
    }
}
