package annotation.json.processor;

import annotation.EntityModelDecoratorInterface;
import model.EntityModel;
import model.EntityModelContext;

public class JsonEntity implements EntityModelDecoratorInterface {

    @Override
    public void updateModel(EntityModel model, EntityModelContext context) {
        // model.add(this.serializer())
        // model.add(this.jsonSerializer())
    }
}
