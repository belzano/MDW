package annotation;

import com.google.common.collect.ImmutableMap;
import generation.TargetOutput;
import generation.writer.HeaderWriter;
import model.EntityModelContext;
import model.EntityTypeModel;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.util.Map;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@EntityTypeDecorator(decorators = Header.Decorator.class)
public @interface Header {

    String[] comments() default {};

    class Decorator implements TypeDecorator {

        static private Map<TargetOutput, String> COMMENT_PREFIX = ImmutableMap.<TargetOutput, String>builder()
                .put(TargetOutput.CPP, "//")
                .put(TargetOutput.HPP, "//")
                .put(TargetOutput.JAVA, "//")
                .put(TargetOutput.CMAKE, "#")
                .build();

        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {
            for (TargetOutput target : TargetOutput.values()) {
                String commentPrefix = COMMENT_PREFIX.get(target);
                model.addWriter(target, new HeaderWriter(commentPrefix));
            }
        }
    }
}
