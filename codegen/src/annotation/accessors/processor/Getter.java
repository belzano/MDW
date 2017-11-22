package annotation.accessors.processor;


import annotation.EntityModelDecoratorInterface;
import annotation.accessors.writer.AccessorWriter;
import model.EntityModel;
import model.EntityModelContext;

public class Getter implements EntityModelDecoratorInterface {

    @Override
    public void updateModel(EntityModel model, EntityModelContext context) {
        model.addWriter(new AccessorWriter());
    }
}
