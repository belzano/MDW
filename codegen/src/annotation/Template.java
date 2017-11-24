package annotation;

import com.google.common.collect.ImmutableList;
import model.EntityDataField;
import model.EntityModelContext;
import model.EntityTypeDescriptor;
import model.EntityTypeModel;

import java.lang.annotation.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@EntityTypeDecorator(decorators = Template.Decorator.class)
public @interface Template {

    class Decorator implements TypeDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {

            for (Field field: model.getEntityClass().getDeclaredFields()) {
                for (Annotation annotation : field.getAnnotations()) {
                    EntityFieldDecorator codegenAnnotation = asFieldDecorator(annotation);
                    if (codegenAnnotation == null) {
                        continue;
                    }
                    for(FieldDecorator processor : getProcessors(codegenAnnotation)) {
                        processor.updateModel(model, context);
                    }
                }

                if (field.getDeclaringClass() == model.getEntityClass()) {
                    EntityDataField df = new EntityDataField(EntityTypeDescriptor.of(field.getType()), field.getName());
                    df.addAnnotations(ImmutableList.copyOf(field.getAnnotations()));
                    model.addDataField(df);
                }
            }
        }

        private EntityFieldDecorator asFieldDecorator(Annotation annotation) {
            EntityFieldDecorator codegenAnnotation = annotation.annotationType().getAnnotation(EntityFieldDecorator.class);
            return codegenAnnotation;
        }

        private List<FieldDecorator> getProcessors(EntityFieldDecorator codegenAnnotation) {
            try {
                Class<? extends FieldDecorator>[] clazzes = codegenAnnotation.decorators();
                List<FieldDecorator> result = new ArrayList<>();
                for (Class<? extends FieldDecorator> clazz:clazzes) {
                    Constructor<? extends FieldDecorator> ctor = clazz.getConstructor();
                    result.add(ctor.newInstance());
                }
                return result;
            } catch (Exception ex) {
                throw new RuntimeException(ex);
            }
        }

    }

}