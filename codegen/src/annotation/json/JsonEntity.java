package annotation.json;

import annotation.EntityTypeDecorator;
import annotation.Template;
import annotation.TypeDecorator;
import annotation.lifecycle.Constructor;
import annotation.lifecycle.Destructor;
import annotation.serialization.Serializable;
import model.EntityTypeModel;
import model.EntityModelContext;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@EntityTypeDecorator(decorators = {Template.Decorator.class,
                                Constructor.Decorator.class,
                                Destructor.Decorator.class,
                                Serializable.Decorator.class,
                                JsonEntity.Decorator.class})
public @interface JsonEntity {

    class Decorator implements TypeDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {
            // model.add(this.serializer())
            // model.add(this.jsonSerializer())
        }
    }

}
