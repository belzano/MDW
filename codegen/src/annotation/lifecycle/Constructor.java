package annotation.lifecycle;

import annotation.EntityTypeDecorator;
import annotation.TypeDecorator;
import model.EntityTypeModel;
import model.EntityModelContext;

import java.lang.annotation.ElementType;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@EntityTypeDecorator(decorators = Constructor.Decorator.class)
public @interface Constructor {

    class Decorator implements TypeDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {

        }
    }

}


