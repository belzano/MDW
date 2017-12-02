package annotation.serialization;

import annotation.EntityTypeDecorator;
import annotation.TypeDecorator;
import model.EntityTypeModel;
import model.EntityModelContext;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@EntityTypeDecorator(decorators = Serializable.Decorator.class)
public @interface Serializable {

    class Decorator implements TypeDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {

        }
    }
}

