package generation.writer;

import model.EntityTypeModel;

public abstract class EntityWriter {

    public abstract String writeEntityContent(EntityTypeModel entityModel);

    public enum Type {
        HEADER,
        CONTENT_LIFECYCLE,
        CONTENT_FEATURES,
        CONTENT_ACCESSORS,
        CONTENT_MEMBERS,
        CONTENT_INTERNAL,
        HELPERS,
        OPERATORS
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
