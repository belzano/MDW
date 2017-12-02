package generation.writer.lifecycle;

import generation.writer.EntityWriter;
import model.EntityTypeModel;

public class LifeCycleWriter extends EntityWriter {

    public LifeCycleWriter() {
        super(Type.LIFECYCLE);
    }

    @Override
    public String writeEntityContent(EntityTypeModel entityModel) {
        return null;
    }
}
