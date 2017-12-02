package annotation;

import com.google.common.collect.ImmutableList;
import model.*;

import java.lang.annotation.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@EntityTypeDecorator(decorators = Template.Decorator.class)
public @interface Template {

    class Decorator implements TypeDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {

            for (Field field: model.getEntityClass().getDeclaredFields()) {

                if (field.getDeclaringClass() != model.getEntityClass()) {
                    continue;
                }

                Set<Class<? extends Annotation>> codegenAnnotations = AnnotationCollector.collectFieldTypeAnnotation(field);

                for(FieldDecorator processor : AnnotationCollector.getFieldTypeProcessors(codegenAnnotations)) {
                    processor.updateModel(model, context);
                }

                EntityDataField df = new EntityDataField(EntityTypeDescriptor.of(field.getType()), field.getName());
                df.addAnnotations(codegenAnnotations);
                model.addDataField(df);

            }
        }

    }

}