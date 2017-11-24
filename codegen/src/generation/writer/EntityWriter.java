package generation.writer;

import model.EntityTypeModel;

public abstract class EntityWriter {

    public abstract String writeEntityContent(EntityTypeModel entityModel);

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
