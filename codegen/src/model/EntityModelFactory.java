package model;

import annotation.TypeDecorator;

import java.lang.annotation.Annotation;
import java.util.Set;

public class EntityModelFactory {

    public EntityModelContext buildContext(String projectName, Set<Class<?>> codeGenClasses) throws Exception {

        EntityModelContext context = new EntityModelContext(projectName);

        for (Class<?> clazz : codeGenClasses) {

            Set<Class<? extends Annotation>> codegenAnnotations = AnnotationCollector.collectClassEntityTypeAnnotation(clazz);
            if (codegenAnnotations.isEmpty()) {
                continue;
            }

            EntityTypeModel model = new EntityTypeModel(clazz, codegenAnnotations);
            context.getEntityModels().add(model);

            for (TypeDecorator processor : AnnotationCollector.getEntityTypeProcessors(codegenAnnotations)) {
                processor.updateModel(model, context);
            }
        }
        return context;
    }

}
