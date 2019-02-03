<?php

namespace App\Controller;

use App\Entity\Temperature;
use App\Repository\TemperatureRepository;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Annotation\Route;

class TemperatureController extends AbstractController
{
    public function index(TemperatureRepository $repository)
    {
        $items = $repository->findBy([],['date'=>'desc'], 10);


        return $this->render('temperature/index.html.twig', [
            'items' => $items,
        ]);
    }

    public function add(Request $request){

        try {
            $entityManager = $this->getDoctrine()->getManager();

            $temperature = new Temperature();
            $temperature->setDate(new \DateTime());
            $temperature->setValue($request->get('temp'));

            $entityManager->persist($temperature);
            $entityManager->flush();
            return $this->json(['status' => 'OK']);
        }catch(\Exception $e) {
            return $this->json([
               'status' => 'Failed',
                'message' => $e->getMessage(),
            ]);
        }
    }
}
