package generation.writer;

import model.EntityTypeModel;

public abstract class EntityWriter {

    public abstract String writeEntityContent(EntityTypeModel entityModel);


    public enum TypeGroup {
        HEADER,
        CONTENT,
        AFTER,
    }

    public enum Type {
        HEADER(TypeGroup.HEADER),
        LIFECYCLE(TypeGroup.CONTENT),
        FEATURES(TypeGroup.CONTENT),
        ACCESSORS(TypeGroup.CONTENT),
        MEMBERS(TypeGroup.CONTENT),
        INTERNAL(TypeGroup.CONTENT),
        HELPERS(TypeGroup.AFTER),
        OPERATORS(TypeGroup.AFTER);

        TypeGroup _group;

        Type(TypeGroup group) {
            _group = group;
        }

        public TypeGroup getGroup() {
            return _group;
        }
    }


    protected Type _type;

    protected EntityWriter(Type type){
        _type = type;
    }

    public Type getType() {
        return _type;
    }

    @Override
    public boolean equals(Object o) {
        return this.getClass().equals(o.getClass());
    }

    @Override
    public int hashCode() {
        String className = this.getClass().getSimpleName();
        return className.hashCode();
    }

}
