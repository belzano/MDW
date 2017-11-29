package annotation.json;

import annotation.EntityTypeDecorator;
import annotation.Template;
import annotation.lifecycle.Constructor;
import annotation.lifecycle.Destructor;
import annotation.serialization.Serializable;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Constructor
@EntityTypeDecorator(extend = {Template.class,
                               Constructor.class,
                               Destructor.class,
                               Serializable.class,
                               Constructor.class})
public @interface JsonEntity {

}
