'use client';
import React, { useState } from 'react';
import { useParams } from 'react-router-dom';
import { Container } from 'react-bootstrap';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import { Formik } from 'formik';
import * as Yup from 'yup';
import { useNavigate } from "react-router-dom";

const CardImageNew = () => {
    const navigate = useNavigate();
    const { id } = useParams();
    const [loading, setLoading] = useState(false);

    if (loading) {
        return (
            <Container>
                <h2>Loading...</h2>
            </Container>
        );
    }

    const validationSchema = Yup.object({
        front: Yup.string()
            .required('A frente é obrigatória.')
            .min(3, 'O título deve ter pelo menos 3 caracteres.'),
        file: Yup.mixed()
            .required('Uma imagem é obrigatória.')
            .test('fileFormat', 'Formato não suportado.', (value) =>
                value ? ['image/jpeg', 'image/png', 'image/gif'].includes(value.type) : false
            ),
    });

    return (
        <Container>
            <h2>Novo Cartão de Imagem</h2>
            <Formik
                initialValues={{
                    front: '',
                    file: null,
                }}
                validationSchema={validationSchema}
                onSubmit={async (values, { setSubmitting }) => {
                    const formData = new FormData();
                    formData.append('front', values.front);
                    formData.append('deckId', id);
                    formData.append('image', values.file);

                    try {
                        const response = await fetch(`http://localhost:3000/api/image`, {
                            method: 'POST',
                            body: formData,
                        });

                        if (!response.ok) {
                            throw new Error('Falha ao salvar o cartão de imagem');
                        }
                        navigate(`/edit/deck/${id}`);
                    } catch (error) {
                        console.error('Erro ao salvar o cartão:', error);
                    }

                    setSubmitting(false);
                }}
            >
                {({
                    values,
                    errors,
                    touched,
                    handleChange,
                    handleBlur,
                    setFieldValue,
                    handleSubmit,
                    isSubmitting,
                }) => (
                    <Form onSubmit={handleSubmit}>
                        <Form.Group className="mb-3" controlId="formBasicTitle">
                            <Form.Label>Frente</Form.Label>
                            <Form.Control
                                type="text"
                                name="front"
                                placeholder="Adicione a frente do cartão"
                                value={values.front}
                                onChange={handleChange}
                                onBlur={handleBlur}
                                isInvalid={touched.front && !!errors.front}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.front}
                            </Form.Control.Feedback>
                        </Form.Group>

                        <Form.Group className="mb-3">
                            <Form.Label>Selecione uma imagem</Form.Label>
                            <Form.Control
                                type="file"
                                name="file"
                                onChange={(e) => setFieldValue('file', e.target.files[0])}
                                onBlur={handleBlur}
                                isInvalid={touched.file && !!errors.file}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.file}
                            </Form.Control.Feedback>
                        </Form.Group>

                        <Button variant="secondary" type="submit" size="lg" disabled={isSubmitting}>
                            {isSubmitting ? 'Salvando...' : 'Salvar'}
                        </Button>
                    </Form>
                )}
            </Formik>
        </Container>
    );
};

export default CardImageNew;
