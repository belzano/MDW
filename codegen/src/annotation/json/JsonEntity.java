package annotation.json;

import annotation.EntityModelDecorator;
import annotation.serialization.Serializable;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Serializable
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@EntityModelDecorator(decorator = annotation.json.processor.JsonEntity.class)
public @interface JsonEntity {

}
