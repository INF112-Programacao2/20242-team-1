'use client';
import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { Container } from 'react-bootstrap';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import { Formik } from 'formik';
import * as Yup from 'yup';

const CardEdit = () => {
    const { id } = useParams();
    const [loading, setLoading] = useState(true);
    const [data, setData] = useState(null);

    // Schema de validação
    const validationSchema = Yup.object({
        front: Yup.string()
            .required('A frente é obrigatória.')
            .min(3, 'O título deve ter pelo menos 3 caracteres.'),
        back: Yup.string()
            .required('O assunto é obrigatório.')
            .min(3, 'O assunto deve ter pelo menos 3 caracteres.'),
    });

    useEffect(() => {
        async function fetchData() {
            if (id) {
                try {
                    const response = await fetch(`http://localhost:3000/api/card/${id}`);
                    const result = await response.json();
                    setData(result);
                } catch (error) {
                    console.error('Error fetching data:', error);
                } finally {
                    setLoading(false);
                }
            } else {
                setLoading(false);
            }
        }

        fetchData();
    }, [id]);

    if (loading) {
        return (
            <Container>
                <h2>Carregando...</h2>
            </Container>
        );
    }

    if (!data && id) {
        return (
            <Container>
                <h2>Nenhum dado encontrado</h2>
            </Container>
        );
    }

    return (
        <Container>
            <h2>Editar Cartão</h2>
            <Formik
                initialValues={{
                    front: data?.front || '',
                    back: data?.back || '',
                }}
                validationSchema={validationSchema}
                onSubmit={async (values, { setSubmitting }) => {
                    const formData = new FormData();
                    formData.append('front', values.front);
                    formData.append('back', values.back);

                    try {
                        const response = await fetch(`http://localhost:3000/api/card/${id}`, {
                            method: 'PUT',
                            body: formData,
                        });

                        if (!response.ok) {
                            throw new Error('Falha ao salvar o cartão');
                        }
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
                    handleSubmit,
                    isSubmitting,
                }) => (
                    <Form onSubmit={handleSubmit}>
                        <Form.Group className="mb-3" controlId="formBasicFront">
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

                        <Form.Group className="mb-3" controlId="formBasicBack">
                            <Form.Label>Verso</Form.Label>
                            <Form.Control
                                type="text"
                                name="back"
                                placeholder="Adicione o verso do cartão"
                                value={values.back}
                                onChange={handleChange}
                                onBlur={handleBlur}
                                isInvalid={touched.back && !!errors.back}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.back}
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

export default CardEdit;
