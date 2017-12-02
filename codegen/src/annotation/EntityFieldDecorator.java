package annotation;

import java.lang.annotation.*;

@Target(ElementType.ANNOTATION_TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface EntityFieldDecorator {
    Class<? extends FieldDecorator>[] decorators() default {};
    Class<? extends Annotation>[] extend() default {};
}
